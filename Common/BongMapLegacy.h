#pragma once

#include <iostream>
#include <array>

/// -- the original implementation used fread/fwrite with global variables, but
/// spiritually it was a fixed size struct
/// this is forward/backwards incompatible if we change the size of the data arrays or add or remove an object type
/// but it worked at the time
struct BongMapLegacy
{
    static const int GoalsArraySize = 3000u;
    static const int BrickArraySize = 3000u;
    static const int BlockArraySize = 3000u;
    static const int BallArraySize = 500u;
    static const int EssenceArraySize = 3000u;
    static const int BouncerArraySize = 3000u;
    static const int PaddleArraySize = 4u;
    static const int DefaultMapBarrier = 1000u;

    int mapBarrier = DefaultMapBarrier;
    paddle bluePaddle;
    paddle redPaddle;
    std::array<goal, GoalsArraySize> redGoals;
    std::array<goal, GoalsArraySize> blueGoals;
    std::array<brick, BrickArraySize> bricks;
    std::array<brick, BlockArraySize> blocks;
    std::array<bouncer, BouncerArraySize> bouncers;
    std::array<essence, EssenceArraySize> redEssences;
    std::array<essence, EssenceArraySize> blueEssences;
    std::array<paddle, PaddleArraySize> redPaddles;
    std::array<paddle, PaddleArraySize> bluePaddles;
    std::array<ball, BallArraySize> balls;

    char imgString[100];
    char musString[100];

    // Define a macro to read from the input stream with error checking
#define READ_FROM_STREAM(var) \
        if (!in.read(reinterpret_cast<char*>(&var), sizeof(var))) { \
            throw std::runtime_error("Failed to read " #var " from input stream"); \
        }

    BongMapLegacy()
    {
    }

    BongMapLegacy(std::istream& in)
    {
        READ_FROM_STREAM(mapBarrier);
        READ_FROM_STREAM(bluePaddle);
        READ_FROM_STREAM(redPaddle);
        READ_FROM_STREAM(redGoals);
        READ_FROM_STREAM(blueGoals);
        READ_FROM_STREAM(bricks);
        READ_FROM_STREAM(blocks);
        READ_FROM_STREAM(bouncers);
        READ_FROM_STREAM(redEssences);
        READ_FROM_STREAM(blueEssences);
        READ_FROM_STREAM(redPaddles);
        READ_FROM_STREAM(bluePaddles);
        READ_FROM_STREAM(balls);
        READ_FROM_STREAM(imgString);
        READ_FROM_STREAM(musString);
    }
#undef READ_FROM_STREAM

#define WRITE_TO_STREAM(var) \
        if (!out.write(reinterpret_cast<const char*>(&var), sizeof(var))) { \
            throw std::runtime_error("Failed to write " #var " to output stream"); \
        }

    void writeToStream(std::ostream& out) const
    {
        WRITE_TO_STREAM(mapBarrier);
        WRITE_TO_STREAM(bluePaddle);
        WRITE_TO_STREAM(redPaddle);
        WRITE_TO_STREAM(redGoals);
        WRITE_TO_STREAM(blueGoals);
        WRITE_TO_STREAM(bricks);
        WRITE_TO_STREAM(blocks);
        WRITE_TO_STREAM(bouncers);
        WRITE_TO_STREAM(redEssences);
        WRITE_TO_STREAM(blueEssences);
        WRITE_TO_STREAM(redPaddles);
        WRITE_TO_STREAM(bluePaddles);
        WRITE_TO_STREAM(balls);
        WRITE_TO_STREAM(imgString);
        WRITE_TO_STREAM(musString);
    }
#undef WRITE_TO_STREAM
};

