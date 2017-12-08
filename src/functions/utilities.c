// -*- coding:utf-8 -*-

#include <nnablart/functions.h>

float getFloat(rt_param_t* param, nn_size_t pos)
{
    return GET_FLOAT(param, pos);
}

float getInt16(rt_param_t* param, nn_size_t pos)
{
    return GET_INT16(param, pos);
}

float getInt8(rt_param_t* param, nn_size_t pos)
{
    return GET_INT8(param, pos);
}

float getSign(rt_param_t* param, nn_size_t pos)
{
    if((*((uint32_t*)(param->data) + (pos / 32))) & (1 << (pos % 32))) {
        return 1;
    }
    return -1;
}

void setFloat(rt_param_t* param, nn_size_t pos, float value)
{
    *((float*)(param->data) + pos) = value;
}

void setInt16(rt_param_t* param, nn_size_t pos, float value)
{
    *((int16_t*)(param->data) + pos) = (int16_t)(value / param->coefficient);
}

void setInt8(rt_param_t* param, nn_size_t pos, float value)
{
    *((int8_t*)(param->data) + pos) = (int8_t)(value / param->coefficient);
}

void setSign(rt_param_t* param, nn_size_t pos, float value)
{
    if(value >= 0) {
        *((uint32_t*)(param->data) + (pos / 32)) |= 1 << (pos % 32);
    } else {
        *((uint32_t*)(param->data) + (pos / 32)) &= ~(1 << (pos % 32));
    }
}
