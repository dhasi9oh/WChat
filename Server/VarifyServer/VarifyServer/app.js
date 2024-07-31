const config_module = require('./config');
const email_module = require('./email');
const const_module = require('./const');
const redis_module = require('./redis');
const message_module = require('./proto');
const { v4: uuidv4 } = require('uuid');
const grpc = require('@grpc/grpc-js');

console.log("confi_module is ", config_module.redis_host, config_module.redis_port);

async function getVarifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try {
        let query_res = await redis_module.GetRedis(const_module.code_prefix + call.request.email);
        console.log("query_res is ", query_res)
        let uniqueId = uuidv4();
        if (query_res == null) {
            if (uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0, 4);
            }
            let bres = await redis_module.SetRedis(const_module.code_prefix + call.request.email, uniqueId, 600)
            if (!bres) {
                callback(null, {
                    email: call.request.email,
                    error: const_module.Errors.RedisErr
                });
                return;
            }
        }
        else {
            uniqueId = query_res;
        }
        console.log("uniqueId is ", uniqueId)
        let text_str = 'Your verification code is ' + uniqueId + '. Please register within three minutes.'
        //发送邮件
        let mailOptions = {
            from: config_module.email_user,
            to: call.request.email,
            subject: '验证码',
            text: text_str,
        };
        let send_res = await email_module.sendEmail(mailOptions);
        console.log("send res is ", send_res)
        callback(null, {
            email: call.request.email,
            error: const_module.Errors.Success
        });
    } catch (error) {
        console.log("catch error is ", error)
        callback(null, {
            email: call.request.email,
            error: const_module.Errors.Exception
        });
    }
}

function main() {
    const server = new grpc.Server();
    server.addService(message_module.VarifyService.service, { GetVarifyCode: getVarifyCode });
    server.bindAsync(config_module.verify_server_ip, grpc.ServerCredentials.createInsecure(), () => {
        server.start();
        console.log("Server started");
    });
}

main();