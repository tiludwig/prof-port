/*
 ******************************************************************************
 File:     main.cpp
 Info:     Generated by Atollic TrueSTUDIO(R) 9.0.0   2019-03-19

 The MIT License (MIT)
 Copyright (c) 2018 STMicroelectronics

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

 ******************************************************************************
 */

/* Includes */
#include "stm32f10x.h"

#include <Core/CommandReceiver/CommandReceiver.h>
#include <Components/ComLink/SerialLink.h>
#include <Components/Target/Target.h>
#include <Core/Buffer/basic_buffer.h>
#include <Core/Stream/streamreader.h>

class TestTarget: public Target
{
public:
	virtual void initialize()
	{
	}

	virtual void startProcessCycle()
	{
	}
	virtual void waitForCycleToEnd()
	{
	}

	virtual void accept()
	{
		buffer.push_back('a');
	}
};

int main()
{
	SerialLink link;
	link.initialize();

	TestTarget target;

	CommandReceiver receiver;
	receiver.registerComponent(1, &target);

	char data[7];
	buffer_t<char> buf(data, 7);
	buf.push_back('#');
	buf.push_back(1);
	buf.push_back(2);
	buf.push_back(0);
	buf.push_back('t');
	buf.push_back('l');
	buf.push_back(29);

	streamreader reader(buf);

	auto marker = reader.read<char>();
	auto id = reader.read<char>();
	auto size = reader.read<uint16_t>();
	auto first = reader.read<char>();
	auto second = reader.read<char>();
	auto checksum = reader.read<uint8_t>();

	while (true)
	{
		//auto data = link.read();
		for (int i = 0; i < 7; i++)
			receiver.process(data[i]);
	}

	return 0;
}
