const fs = require('fs');
let config = JSON.parse(fs.readFileSync('config.json', 'utf8'));
let email_user = config.email.user;
let email_pass = config.email.pass;
let redis_host = config.redis.host;
let redis_port = config.redis.port;
let redis_passwd = config.redis.passwd;
let verify_server_ip = config.VerifyServer.host + ":" + config.VerifyServer.port;
let code_prefix = "code_";

module.exports = {
    email_user,
    email_pass,
    redis_host,
    redis_port,
    redis_passwd,
    code_prefix,
    verify_server_ip
}