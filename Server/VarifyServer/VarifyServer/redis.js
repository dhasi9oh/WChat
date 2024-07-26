const Redis = require("ioredis");
const config = require("./config");

// ����Redis�ͻ���ʵ��
const RedisClient = new Redis({
    host: config.redis.host,
    port: config.redis.port,
    password: config.redis.password,

    enableOfflineQueue: false, // ����������Ϣ����
    enableReadyCheck: true, // ���ü�������Ƿ����
});

RedisClient.on("error", (error) => {
    console.error("Redis Error:", error);

    // ������������
    RedisClient.connect();
});

setInterval(() => {
    RedisClient.set("heartbeat", Date.now());
}, 1000 * 60); // ÿ���ӷ���һ��������

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
        // ���ù���ʱ��
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