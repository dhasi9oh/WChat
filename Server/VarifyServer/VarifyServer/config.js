const fs = require('fs');
let config = JSON.parse(fs.readFileSync('config.json', 'utf8'));
let email_user = config.email.user;
let email_pass = config.email.pass;
let redis_host = config.redis.host;
let redis_port = config.redis.port;
let redis_passwd = config.redis.passwd;
let verify_server_ip = config.VerifyServer.host + ":" + config.VerifyServer.port;

console.log("email_user: " + email_user);
console.log("email_pass: " + email_pass);
console.log("redis_host: " + redis_host);
console.log("redis_port: " + redis_port);
console.log("redis_passwd: " + redis_passwd);

module.exports = {
    email_user,
    email_pass,
    redis_host,
    redis_port,
    redis_passwd,
    verify_server_ip
}