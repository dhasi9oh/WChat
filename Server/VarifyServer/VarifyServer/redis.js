const Redis = require("ioredis");
const config = require("./config");

// 创建Redis客户端实例
const RedisClient = new Redis({
    host: config.redis.host,
    port: config.redis.port,
    password: config.redis.password,

    enableOfflineQueue: false, // 禁用离线消息队列
    enableReadyCheck: true, // 启用检查连接是否可用
});

RedisClient.on("error", (error) => {
    console.error("Redis Error:", error);

    // 尝试重新连接
    RedisClient.connect();
});

setInterval(() => {
    RedisClient.set("heartbeat", Date.now());
}, 1000 * 60); // 每分钟发送一次心跳包

async function GetRedis(key) {
    try {
        const result = await RedisClient.get(key);
        if (result === null) {
            console.log('result:', '<' + result + '>', 'This key cannot be find...')
            return null
        }
        console.log('Result:', '<' + result + '>', 'Get key success!...');
        return result
    }
    catch (error) {
        console.error('Get key error:', error);
        return null
    }
}

async function ExistRedis(key) {
    try {
        const result = await RedisClient.exists(key);
        if (result === 0) {
            console.log('result:<', '<' + result + '>', 'This key is null...');
            return null
        }
        console.log('Result:', '<' + result + '>', 'With this value!...');
        return result
    }
    catch (error) {
        console.log('Exist key error is', error);
        return null
    }
}


async function SetRedis(key, value, expireTime) {
    try {
        await RedisClient.set(key, value);
        // 设置过期时间
        await RedisClient.expire(key, expireTime);
        return true
    }
    catch (error) {
        console.error('Set key error:', error);
        return false
    }
}

module.exports = {
    GetRedis,
    ExistRedis,
    SetRedis
};