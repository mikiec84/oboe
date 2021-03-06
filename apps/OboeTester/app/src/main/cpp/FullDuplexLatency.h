/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OBOETESTER_FULL_DUPLEX_LATENCY_H
#define OBOETESTER_FULL_DUPLEX_LATENCY_H

#include <unistd.h>
#include <sys/types.h>

#include "oboe/Oboe.h"
#include "FullDuplexStream.h"
#include "InterpolatingDelayLine.h"
#include "LatencyAnalyzer.h"

class FullDuplexLatency : public FullDuplexStream {
public:
    FullDuplexLatency() {}

    /**
     * Called when data is available on both streams.
     * Caller should override this method.
     */
    oboe::DataCallbackResult onBothStreamsReady(
            const void *inputData,
            int   numInputFrames,
            void *outputData,
            int   numOutputFrames
    ) override;

    oboe::Result start() override;

    void report() {
        mEchoAnalyzer.report();
    }

    bool isDone() {
        return mEchoAnalyzer.isDone();
    }

    void analyzeData() {
        mEchoAnalyzer.report();
    }

    LatencyAnalyzer *getLatencyAnalyzer() {
        return &mEchoAnalyzer;
    }

private:

    EchoAnalyzer  mEchoAnalyzer;

};


#endif //OBOETESTER_FULL_DUPLEX_LATENCY_H
