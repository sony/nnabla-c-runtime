// -*- coding:utf-8 -*-
#ifndef H_ACCESOR_H_171210064532_
#define H_ACCESOR_H_171210064532_

#define GET_FLOAT(xVariable, xPos) (*((float *)((xVariable)->data) + (xPos)))
#define GET_INT16(xVariable, xPos)                                                \
  ((xVariable)->coefficient * (float)(*((int16_t *)((xVariable)->data) + (xPos))))
#define GET_INT8(xVariable, xPos)                                                 \
  ((xVariable)->coefficient * (float)(*((int8_t *)((xVariable)->data) + (xPos))))
#define GET_SIGN(xVariable, xPos) getSign(xVariable, xPos)

float getFloat(rt_variable_t *variable, nn_size_t pos);
float getInt16(rt_variable_t *variable, nn_size_t pos);
float getInt8(rt_variable_t *variable, nn_size_t pos);
float getSign(rt_variable_t *variable, nn_size_t pos);

void setFloat(rt_variable_t *variable, nn_size_t pos, float value);
void setInt16(rt_variable_t *variable, nn_size_t pos, float value);
void setInt8(rt_variable_t *variable, nn_size_t pos, float value);
void setSign(rt_variable_t *variable, nn_size_t pos, float value);

typedef float (*rt_variable_getter)(struct rt_variable_t *, nn_size_t);
rt_variable_getter select_getter(nn_data_type_t data_type);

typedef void (*rt_variable_setter)(struct rt_variable_t *, nn_size_t, float);
rt_variable_setter select_setter(nn_data_type_t data_type);

#endif // H_ACCESOR_H_171210064532_

