#pragma once

struct DriftItem{
    float x;
    float y;
};

struct PredictionParticle{
    DriftItem pos;
    float weight;
};