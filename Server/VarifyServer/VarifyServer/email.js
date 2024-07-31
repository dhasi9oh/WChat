const nodemailer = require('nodemailer');
const config = require('./config');

let transporter = nodemailer.createTransport({
    host: "smtp.qq.com",
    port: 465,
    secure: true,
    auth: {
        user: config.email_user,
        pass: config.email_pass
    }
});

function sendEmail(mailOptions) {
    return new Promise((resolve, reject) => {
        transporter.sendMail(mailOptions, (error, info) => {
            if (error) {
                reject(error);
            } else {
                resolve(info);
            }
        });
    });
}

module.exports = {
    sendEmail
};