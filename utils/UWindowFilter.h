/*
 * UWindowFilter.h
 *
 *  Created on: 2018年3月31日
 *      Author: Romeli
 */

#ifndef MATH_UWINDOWFILTER_H_
#define MATH_UWINDOWFILTER_H_
#include <QObject>

template<typename T>
class UWindowFilter {
public:
	UWindowFilter() {
		_sum = 0;
		_sp = 0;
		_size = 0;
		_buffer = nullptr;
	}
	UWindowFilter(uint8_t size) {
		_buffer = nullptr;
		Init(size);
	}
	~UWindowFilter() {
		delete[] _buffer;
	}

	void Init(uint8_t size) {
		_sum = 0;
		_sp = 0;
		_size = size;
		if (_buffer != nullptr) {
			delete[] _buffer;
		}
		if (_size != 0) {
			_buffer = new T[size];
			for (uint8_t i = 0; i < _size; ++i) {
				_buffer[i] = 0;
			}
		}
	}

	T Get(T input) {
		if (_buffer == nullptr) {
			return input;
		} else {
			//从和中删除最后一个数
			_sum -= _buffer[_sp];
			//将当前数据移入缓冲
			_buffer[_sp] = input;
			_sum += _buffer[_sp];
			//移动缓冲指针
			_sp = (_sp + 1) % _size;
			//返回平均数
			return _sum / _size;
		}
	}

	void Clear(T defValue = 0) {
        for (uint8_t i = 0; i < _size; ++i) {
            _buffer[i] = defValue;
        }
	}
private:
	T *_buffer;
	T _sum;
	uint8_t _size;
	uint8_t _sp;
};

#endif /* MATH_UWINDOWFILTER_H_ */
