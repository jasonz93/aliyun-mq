{
    "targets": [
        {
            "target_name": "alimq",
            "sources": [
                "src/utils.cc",
                "src/alimq.cc",
                "src/ONSFactoryWrap.cc",
                "src/ProducerWrap.cc",
                "src/MessageWrap.cc",
                "src/async_workers/producer_send.cc",
                "src/PushConsumerWrap.cc",
                "src/BaseMessageListener.cc",
                "src/MessageAck.cpp"
            ],
            "cflags_cc!": ["-fno-exceptions", "-pthread", "-Wl,--no-as-needed", "-ldl", "-luv"],
            "cflags_cc": [ "-Wno-ignored-qualifiers" ],
            "cflags": [ "-std=c++11", "-g" ],
            "libraries": [
                "../sdk/lib/lib-boost-static/libonsclient4cpp.a"
            ],
            "include_dirs" : [
                "<!(node -e \"require('nan')\")",
                "sdk/include"
            ]
        }
    ]
}