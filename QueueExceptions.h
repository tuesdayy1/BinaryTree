#pragma once
#include <iostream>


class QueueUnderFlow : public std::exception {
private:
	std::string message_ = "QueueUnderFlow: cannot take element, queue is empty";

public:
	const char* what() const override {
		return message_.c_str();
	}
};