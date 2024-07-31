const path = require('path');
const grpc = require('@grpc/grpc-js');
const grpcLoader = require('@grpc/proto-loader');

const PROTO_PATH = path.join(__dirname, 'message.proto');
const packageDefinition = grpcLoader.loadSync(
  PROTO_PATH,
  {
    keepCase: true,
    longs: String,
    enums: String,
    defaults: true,
    oneofs: true
  }
);

const message = grpc.loadPackageDefinition(packageDefinition).message;

module.exports = message;