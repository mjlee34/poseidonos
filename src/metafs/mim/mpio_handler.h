/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Samsung Electronics Corporation nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "mfs_io_handler_base.h"
#include "metafs_io_q.h"
#include "mpio_pool.h"
#include "src/telemetry/telemetry_client/telemetry_publisher.h"

#include <string>

namespace pos
{
class MpioHandler
{
public:
    explicit MpioHandler(int threadId, int coreId,
                    TelemetryPublisher* tp = nullptr,
                    MetaFsIoQ<Mpio*>* doneQ = nullptr);
    ~MpioHandler(void);

    void EnqueuePartialMpio(Mpio* mpio);
    void BindMpioPool(MpioPool* mpioPool);
    void BottomhalfMioProcessing(void);

private:
    void _InitPartialMpioDoneQ(size_t mpioDoneQSize);
    void _SendMetric(uint32_t size);

    MetaFsIoQ<Mpio*>* partialMpioDoneQ;
    MpioPool* mpioPool;
    int coreId;
    TelemetryPublisher* telemetryPublisher = nullptr;
    std::chrono::steady_clock::time_point lastTime;
    std::string nameForTelemetry = "";
};
} // namespace pos
