#pragma once
#include <iostream>

class StackUnderFlow : public std::exception {
private:
	std::string message_ = "StackUnderFlow: Cannot pop element, stack is empty.";

public:
	const char* what() const override {
		return message_.c_str();
	}
};