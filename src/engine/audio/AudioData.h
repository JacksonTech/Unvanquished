/*
===========================================================================
Daemon BSD Source Code
Copyright (c) 2014, Theodoros Theodoridis <theodoridisgr@gmail.com>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Daemon developers nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL DAEMON DEVELOPERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
===========================================================================
*/

#ifndef AUDIO_DATA_H
#define AUDIO_DATA_H

namespace Audio {

struct AudioData {
	AudioData()
	    : sampleRate{0}
	    , byteDepth{0}
	    , numberOfChannels{0}
	    , size{0}
	    , rawSamples{nullptr}
	    , memoryOwned{false}
	{}

	AudioData(int sampleRate, int byteDepth, int numberOfChannels, int size, const void* rawSamples,
	          bool memoryOwned = true)
	    : sampleRate{sampleRate}
	    , byteDepth{byteDepth}
	    , numberOfChannels{numberOfChannels}
	    , size{size}
	    , rawSamples{rawSamples}
	    , memoryOwned{memoryOwned}
	{}

	AudioData(AudioData&& that)
	    : sampleRate{that.sampleRate}
	    , byteDepth{that.byteDepth}
	    , numberOfChannels{that.numberOfChannels}
	    , size{that.size}
	    , rawSamples{that.rawSamples}
	    , memoryOwned{that.memoryOwned}
	{
		that.memoryOwned = false;
	}

	AudioData(const AudioData& that) = delete;

	~AudioData()
	{
		if (memoryOwned && rawSamples != nullptr)
			delete[] static_cast<const char*>(rawSamples);
	}
	const int sampleRate;
	const int byteDepth;
	const int numberOfChannels;
	const int size;
	const void* rawSamples;

private:
	bool memoryOwned; // if the memory is owned then it must be deleted during destruction
};
} // namespace Audio
#endif
