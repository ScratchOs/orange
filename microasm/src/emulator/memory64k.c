#include "emulator/memory64k.h"
#include "shared/memory.h"
#include "shared/platform.h"
#include <stdlib.h>

typedef struct memCtx {
    unsigned int addressBus; 
    unsigned int dataBus;
    Memory64k* mem;
} memCtx;

static void memoryRead(VMCore* core, void* vctx) {
    memCtx* ctx = vctx;
    if(!core->buss[ctx->addressBus].isValid) {
        cErrPrintf(TextRed, "invalid bus read - memrd");
        exit(0);
    }
    core->buss[ctx->dataBus].value = ctx->mem->value[core->buss[ctx->addressBus].value];
    core->buss[ctx->dataBus].isValid = true;
}

static void memoryWrite(VMCore* core, void* vctx) {
    memCtx* ctx = vctx;
    if(!core->buss[ctx->addressBus].isValid || !core->buss[ctx->dataBus].isValid) {
        cErrPrintf(TextRed, "invalid bus read - memwt");
        exit(0);
    }
    ctx->mem->value[core->buss[ctx->addressBus].value] = core->buss[ctx->dataBus].value;
}

unsigned int memoryInit(Memory64k* mem, VMCore* core, unsigned int addressBus, unsigned int dataBus) {
    memCtx* ctx = ArenaAlloc(sizeof(memCtx));
    ctx->addressBus = addressBus;
    ctx->dataBus = dataBus;
    ctx->mem = mem;

    ADD_COMMAND(memoryRead, ctx, &core->buss[addressBus], mem);
    CHANGES(&core->buss[dataBus]);

    ADD_COMMAND(memoryWrite, ctx, &core->buss[addressBus], &core->buss[dataBus]);
    CHANGES(&mem);
    return core->commandCount - 2;
}