//
// Created by flf on 2023/3/24.
//

#include <stdio.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"

AVFormatContext *ifmt_ctx;
AVFormatContext *ofmt_ctx;
AVCodecContext *dec_ctx;
AVCodecContext *enc_ctx;

int video_index = -1;
int audio_index = -1;

static int open_input(const char *url) {
    AVCodec *codec = NULL;
    int ret = 0;

    if ((ret = avformat_open_input(&ifmt_ctx, url, NULL, NULL)) < 0) {
        printf("open input failed\n");
        return ret;
    }

    if ((ret = avformat_find_stream_info(ifmt_ctx, NULL)) < 0) {
        printf("find stream info failed\n");
        return ret;
    }

    if ((ret = av_find_best_stream(ifmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0)) < 0) {
        printf("not find video stream\n");
        return ret;
    }

    video_index = ret;

    if ((ret = av_find_best_stream(ifmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0)) < 0) {
        printf("not find audio stream\n");
        return ret;
    }

    audio_index = ret;

    printf("video_index = %d, audio index = %d\n", video_index, audio_index);

    dec_ctx = avcodec_alloc_context3(codec);
    if (!dec_ctx) {
        printf("create decoder ctx failed\n");
        return -1;
    }

    if ((ret = avcodec_parameters_to_context(dec_ctx, ifmt_ctx->streams[video_index]->codecpar)) < 0) {
        printf("copy params to decoder ctx failed\n");
        return ret;
    }

    printf("--------------------------------------Input-------------------------------------\n");
    av_dump_format(ifmt_ctx, 0, url, 0);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: ./scale filename");
        return -1;
    }

    int ret = -1;
    if ((ret = open_input(argv[1])) < 0) {
        printf("open input %s failed\n", argv[1]);
        return -1;
    }
    return 0;
}