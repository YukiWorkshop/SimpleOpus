/*
    This file is part of SimpleOpus.
    Copyright (C) 2020 ReimuNotMoe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include "SimpleOpus.hpp"

using namespace YukiWorkshop::SimpleOpus;

Encoder::Encoder(int32_t __sample_rate, int __channels, int __application) {
	int err;
	opus_ctx = opus_encoder_create(__sample_rate, __channels, __application, &err);

	if (!opus_ctx)
		throw __OPUS_ERROR(err);
}

Encoder::~Encoder() {
	if (opus_ctx)
		opus_encoder_destroy(opus_ctx);
}

Encoder &Encoder::set_application(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_APPLICATION(__x));
	return *this;
}

Encoder &Encoder::set_bandwidth(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_BANDWIDTH(__x));
	return *this;
}

Encoder &Encoder::set_bitrate(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_BITRATE(__x));
	return *this;
}

Encoder &Encoder::set_complexity(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_COMPLEXITY(__x));
	return *this;
}

Encoder &Encoder::set_dtx(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_DTX(__x));
	return *this;
}

Encoder &Encoder::set_frame_duration(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_EXPERT_FRAME_DURATION(__x));
	return *this;
}

Encoder &Encoder::set_channels(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_FORCE_CHANNELS(__x));
	return *this;
}

Encoder &Encoder::set_inband_fec(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_INBAND_FEC(__x));
	return *this;
}

Encoder &Encoder::set_lsb_depth(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_LSB_DEPTH(__x));
	return *this;
}

Encoder &Encoder::set_max_bandwidth(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_MAX_BANDWIDTH(__x));
	return *this;
}

Encoder &Encoder::set_packet_loss_perc(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_PACKET_LOSS_PERC(__x));
	return *this;
}

Encoder &Encoder::set_prediction_disabled(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_PREDICTION_DISABLED(__x));
	return *this;
}

Encoder &Encoder::set_signal(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_SIGNAL(__x));
	return *this;
}

Encoder &Encoder::set_vbr(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_VBR(__x));
	return *this;
}

Encoder &Encoder::set_vbr_constraint(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_VBR_CONSTRAINT(__x));
	return *this;
}

Encoder &Encoder::set_phase_inversion_disabled(int32_t __x) {
	opus_encoder_ctl(opus_ctx, OPUS_SET_PHASE_INVERSION_DISABLED(__x));
	return *this;
}

void Encoder::reset() {
	opus_encoder_ctl(opus_ctx, OPUS_RESET_STATE);
}

int32_t Encoder::encode(const int16_t *__pcm, int __frame_size, uint8_t *__data, int32_t __max_data_len) {
	return opus_encode(opus_ctx, __pcm, __frame_size, __data, __max_data_len);
}

int32_t Encoder::encode_float(const float *__pcm, int __frame_size, uint8_t *__data, int32_t __max_data_len) {
	return opus_encode_float(opus_ctx, __pcm, __frame_size, __data, __max_data_len);
}

std::vector<uint8_t> Encoder::encode(const int16_t *__pcm, int __frame_size, int32_t __max_data_len) {
	std::vector<uint8_t> ret(__max_data_len);

	auto rc = encode((const int16_t *)__pcm, __frame_size, ret.data(), ret.size());

	if (rc < 0)
		throw __OPUS_ERROR(rc);

	ret.resize(rc);
	return ret;
}

std::vector<uint8_t> Encoder::encode_float(const float *__pcm, int __frame_size, int32_t __max_data_len) {
	std::vector<uint8_t> ret(__max_data_len);

	auto rc = encode_float((const float *)__pcm, __frame_size, ret.data(), ret.size());

	if (rc < 0)
		throw __OPUS_ERROR(rc);

	ret.resize(rc);
	return ret;
}

Decoder::Decoder(int32_t __sample_rate, int __channels) {
	int err;
	opus_ctx = opus_decoder_create(__sample_rate, __channels, &err);

	if (!opus_ctx)
		throw __OPUS_ERROR(err);
}

Decoder::~Decoder() {
	if (opus_ctx)
		opus_decoder_destroy(opus_ctx);
}

Decoder &Decoder::set_gain(int32_t __x) {
	opus_decoder_ctl(opus_ctx, OPUS_SET_GAIN(__x));
	return *this;
}

Decoder &Decoder::set_phase_inversion_disabled(int32_t __x) {
	opus_decoder_ctl(opus_ctx, OPUS_SET_PHASE_INVERSION_DISABLED(__x));
	return *this;
}

int32_t Decoder::last_packet_duration() {
	int32_t ret;
	opus_decoder_ctl(opus_ctx, OPUS_GET_LAST_PACKET_DURATION(&ret));
	return ret;
}

int32_t Decoder::gain() {
	int32_t ret;
	opus_decoder_ctl(opus_ctx, OPUS_GET_GAIN(&ret));
	return ret;
}

int32_t Decoder::pitch() {
	int32_t ret;
	opus_decoder_ctl(opus_ctx, OPUS_GET_PITCH(&ret));
	return ret;
}

void Decoder::reset() {
	opus_decoder_ctl(opus_ctx, OPUS_RESET_STATE);
}

int32_t Decoder::decode(const uint8_t *__data, int32_t __len, int16_t *__pcm, int __frame_size, int __decode_fec) {
	return opus_decode(opus_ctx, __data, __len, __pcm, __frame_size, __decode_fec);
}

int32_t Decoder::decode_float(const uint8_t *__data, int32_t __len, float *__pcm, int __frame_size, int __decode_fec) {
	return opus_decode_float(opus_ctx, __data, __len, __pcm, __frame_size, __decode_fec);
}

std::vector<int16_t> Decoder::decode(const uint8_t *__data, int32_t __len, int __decode_fec, int __max_frame_size) {
	std::vector<int16_t> ret(__max_frame_size);

	auto rc = decode((const uint8_t *)__data, __len, ret.data(), ret.size(), __decode_fec);

	if (rc < 0)
		throw __OPUS_ERROR(rc);

	ret.resize(rc);
	return ret;
}

std::vector<float> Decoder::decode_float(const uint8_t *__data, int32_t __len, int __decode_fec, int __max_frame_size) {
	std::vector<float> ret(__max_frame_size);

	auto rc = decode_float((const uint8_t *)__data, __len, ret.data(), ret.size(), __decode_fec);

	if (rc < 0)
		throw __OPUS_ERROR(rc);

	ret.resize(rc);
	return ret;
}
