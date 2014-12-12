#pragma once

#include <memory>

namespace casm {

	template<typename T, bool checkBounds = false>
	class Array {
	private:
		T* ptr;
	public:

		const unsigned length;

		Array(unsigned length) :
			ptr(new T[length]),
			length(length) {}
		~Array() {
			delete[] ptr;
		}

		T& operator [](unsigned i) const {
			return ptr[i];
		}

	};

}