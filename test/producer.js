/**
 * Created by nicholas on 17-2-20.
 */
const expect = require('chai').expect;
const AliMQ = require('../');

describe('Producer tests', function () {
    let factory;

    it('Test factory create', () => {
        factory = new AliMQ.ONSFactory({
            logPath: './logs',
            accessKey: 'IXqi88QaVEG9iGnV',
            secretKey: 'wA7mJ4drL6dDj9AVC2dDrk4ohEGCXz'
        });
    });

    it('Test push send', function (done) {
        this.timeout(15000);
        let producer = factory.createProducer({
            producerId: 'PID_alimq_test'
        });
        producer.start();
        let consumer = factory.createPushConsumer({
            consumerId: 'CID_alimq_test'
        });
        let msgId;
        consumer.subscribe('agarage', (msg, ack) => {
            expect(msg.body).to.be.equal('this is body');
            ack();
            if (msg.msgId === msgId) {
                producer.shutdown();
                consumer.shutdown();
                done();
            }
        });
        consumer.start();
        producer.send({
            topic: 'agarage',
            body: 'this is body'
        }, (err, result) => {
            console.log('push send', err, result);
            msgId = result.msgId;
            expect(err).to.be.equal(null);
            expect(result.msgId).not.to.be.equal(null);
        });
    });

    it('Test global order send', function (done) {
        this.timeout(30000);
        let producer = factory.createOrderProducer({
            producerId: 'PID_alimq_test_global_order'
        });
        producer.start();
        let consumer = factory.createOrderConsumer({
            consumerId: 'CID_alimq_test_global_order'
        });
        let msgId;
        consumer.subscribe('agarage_global_ordered', (msg, ack) => {
            expect(msg.body).to.be.equal('this is body');
            ack();
            if (msg.msgId === msgId) {
                producer.shutdown();
                consumer.shutdown();
                done();
            }
        });
        consumer.start();
        producer.send({
            topic: 'agarage_global_ordered',
            body: 'this is body'
        }, 'abc', (err, result) => {
            console.log('global order send', err, result);
            msgId = result.msgId;
            expect(err).to.be.equal(null);
            expect(result.msgId).not.to.be.equal(null);
            expect(result.msgId).not.to.be.equal('');
        })
    });
});