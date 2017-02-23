/**
 * Created by nicholas on 17-2-20.
 */

/**
 * @name PushConsumer
 * @class
 */

/**
 * @memberOf PushConsumer#
 * @method start
 */

/**
 * @memberOf PushConsumer#
 * @method shutdown
 */

/**
 * @memberOf PushConsumer#
 * @method subscribe
 * @param {string} topic
 * @param {string} [subExpression]
 * @param {function} listener
 */

/**
 *
 * @name  Producer
 * @class
 */

/**
 * @memberOf Producer#
 * @method start
 */

/**
 * @memberOf Producer#
 * @method shutdown
 */

/**
 *
 * @memberOf Producer#
 * @method send
 * @param {object} msg
 * @param {function} callback
 */

/**
 *
 * @memberOf Producer#
 * @method sendOneway
 * @param {object} msg
 * @param {function} callback
 */

/**
 * @name OrderProducer
 * @class
 */

/**
 * @memberOf OrderProducer#
 * @method start
 */

/**
 * @memberOf OrderProducer#
 * @method shutdown
 */

/**
 * @memberOf OrderProducer#
 * @method send
 * @param {object} msg
 * @param {string} shardingKey
 * @param {function} callback
 */

/**
 * @name OrderConsumer
 * @class
 */

/**
 * @memberOf OrderConsumer#
 * @method start
 */

/**
 * @memberOf OrderConsumer#
 * @method shutdown
 */

/**
 * @memberOf OrderConsumer#
 * @method subscribe
 * @param {string} topic
 * @param {string} subExpression
 * @param {function} listener
 */

/**
 * @memberOf AliMQ
 * @name ONSFactory
 * @class
 * @param {object} options
 */

/**
 * @memberOf ONSFactory#
 * @method createProducer
 * @param {object} options
 * @return Producer
 */

/**
 * @memberOf ONSFactory#
 * @method createPushConsumer
 * @param {object} options
 * @return {PushConsumer}
 */

/**
 * @memberOf ONSFactory#
 * @method createOrderProducer
 * @param {object} options
 * @return OrderProducer
 */

/**
 * @memberOf ONSFactory#
 * @method createOrderConsumer
 * @param {object} options
 * @return OrderConsumer
 */

/**
 * @name AliMQ
 */
module.exports = require('node-cmake')('alimq');
