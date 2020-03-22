/*
    This file is part of SimpleOpus.
    Copyright (C) 2020 ReimuNotMoe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the MIT License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#pragma once

#include <stdexcept>
#include <vector>

#include <cinttypes>

#include <opus/opus.h>

#define __OPUS_ERROR(err)		std::runtime_error(opus_strerror(err))

namespace YukiWorkshop::SimpleOpus {
	class Encoder {
	private:
		OpusEncoder *opus_ctx = nullptr;
	public:
		Encoder(int32_t __sample_rate, int __channels, int __application);
		~Encoder();

		Encoder& set_application(int32_t __x);
		Encoder& set_bandwidth(int32_t __x);
		Encoder& set_bitrate(int32_t __x);
		Encoder& set_complexity(int32_t __x);
		Encoder& set_dtx(int32_t __x);
		Encoder& set_frame_duration(int32_t __x);
		Encoder& set_channels(int32_t __x);
		Encoder& set_inband_fec(int32_t __x);
		Encoder& set_lsb_depth(int32_t __x);
		Encoder& set_max_bandwidth(int32_t __x);
		Encoder& set_packet_loss_perc(int32_t __x);
		Encoder& set_prediction_disabled(int32_t __x);
		Encoder& set_signal(int32_t __x);
		Encoder& set_vbr(int32_t __x);
		Encoder& set_vbr_constraint(int32_t __x);
		Encoder& set_phase_inversion_disabled(int32_t __x);

		void reset();

		int32_t encode(const int16_t *__pcm, int __frame_size, uint8_t *__data, int32_t __max_data_len);
		int32_t encode_float(const float *__pcm, int __frame_size, uint8_t *__data, int32_t __max_data_len);
		std::vector<uint8_t> encode(const int16_t *__pcm, int __frame_size, int32_t __max_data_len = 2048);
		std::vector<uint8_t> encode_float(const float *__pcm, int __frame_size, int32_t __max_data_len = 2048);

		template <typename T>
		std::vector<uint8_t> encode(const std::vector<T> __pcm, int32_t __max_data_len = 2048) {
			std::vector<uint8_t> ret(__max_data_len);
			double multiply_factor = (double)sizeof(T) / 2.0;

			auto rc = encode((const int16_t *)__pcm.data(), (size_t)((double)__pcm.size() * multiply_factor), ret.data(), ret.size());

			if (rc < 0)
				throw __OPUS_ERROR(rc);

			ret.resize(rc);
			return ret;
		}

		template <typename T>
		std::vector<uint8_t> encode_float(const std::vector<T> __pcm, int32_t __max_data_len = 2048) {
			std::vector<uint8_t> ret(__max_data_len);
			double multiply_factor = (double)sizeof(T) / 4.0;

			auto rc = encode_float((const float *)__pcm.data(), (size_t)((double)__pcm.size() * multiply_factor), ret.data(), ret.size());

			if (rc < 0)
				throw __OPUS_ERROR(rc);

			ret.resize(rc);
			return ret;
		}
	};

	class Decoder {
	private:
		OpusDecoder *opus_ctx = nullptr;
	public:
		Decoder(int32_t __sample_rate, int __channels);

		~Decoder();

		Decoder& set_gain(int32_t __x);
		Decoder& set_phase_inversion_disabled(int32_t __x);

		int32_t last_packet_duration();
		int32_t gain();
		int32_t pitch();

		void reset();

		int32_t decode(const uint8_t *__data, int32_t __len, int16_t *__pcm, int __frame_size, int __decode_fec = 0);
		int32_t decode_float(const uint8_t *__data, int32_t __len, float *__pcm, int __frame_size, int __decode_fec = 0);
		std::vector<int16_t> decode(const uint8_t *__data, int32_t __len, int __decode_fec = 0, int __max_frame_size = 5760);
		std::vector<float> decode_float(const uint8_t *__data, int32_t __len, int __decode_fec = 0, int __max_frame_size = 5760);

		template <typename T>
		std::vector<int16_t> decode(const std::vector<T> __data, int __decode_fec = 0, int __max_frame_size = 5760) {
			std::vector<int16_t> ret(__max_frame_size);

			auto rc = decode((const uint8_t *)__data.data(), __data.size() * sizeof(T), ret.data(), ret.size(), __decode_fec);

			if (rc < 0)
				throw __OPUS_ERROR(rc);

			ret.resize(rc);
			return ret;
		}

		template <typename T>
		std::vector<float> decode_float(const std::vector<T> __data, int __decode_fec = 0, int __max_frame_size = 5760) {
			std::vector<float> ret(__max_frame_size);

			auto rc = decode_float((const uint8_t *)__data.data(), __data.size() * sizeof(T), ret.data(), ret.size(), __decode_fec);

			if (rc < 0)
				throw __OPUS_ERROR(rc);

			ret.resize(rc);
			return ret;
		}
	};
}