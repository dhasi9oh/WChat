const config_module = require('./config');
const email_module = require('./email');
const const_moudle = require('./const');
const redis_module = require('./redis');
const message_module = require('./proto');
const { v4: uuidv4 } = require('uuid');
const grpc = require('@grpc/grpc-js');


async function GetVarifyCode(call, callback) {
    console.log("email is ", call.request.email)
    try {
        let query_res = await redis_module.GetRedis(const_module.code_prefix + call.request.email);
        console.log("query_res is ", query_res)
        if (query_res == null) {

        }
        let uniqueId = query_res;
        if (query_res == null) {
            uniqueId = uuidv4();
            if (uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0, 4);
            }
            let bres = await redis_module.ExistRedis(const_module.code_prefix + call.request.email, uniqueId, 600)
            if (!bres) {
                callback(null, {
                    email: call.request.email,
                    error: const_module.Errors.RedisErr
                });
                return;
            }
        }

        console.log("uniqueId is ", uniqueId)
        let text_str = '您的验证码为' + uniqueId + '请三分钟内完成注册'
        //发送邮件
        let mailOptions = {
            from: config_module.email_user,
            to: call.request.email,
            subject: '验证码',
            text: text_str,
        };

        let send_res = await email_module.SendMail(mailOptions);
        console.log("send res is ", send_res)

        callback(null, {
            email: call.request.email,
            error: const_moudle.Errors.Success
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
    server.addService(message_module, VarifyService.service, { GetVarifyCode: GetVarifyCode });
    server.bindAsync(config_module.verify_server_ip, grpc.ServerCredentials.createInsecure(), () => {
        server.start();
        console.log("Server started");
    });
}

main();