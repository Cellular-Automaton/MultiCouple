/*
** EPITECH PROJECT, 2023
** CAMI-Desktop/src/communication_test/src
** File description:
** init
*/

#include <Wrapper/WrapperMultiCouple.hh>
#include <WrapperInit.hh>
#include <array>
#include <iostream>
#include <string>

Napi::Float64Array Wrapper::add_wrapped_multi_couple(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env(); // check if arguments are integer only.
    /*    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber()) {
            Napi::TypeError::New(env, "arg1::Number, arg2::Number expected")
                .ThrowAsJavaScriptException();
        }*/ // convert javascripts datatype to c++
    Napi::Float64Array first = info[0].As<Napi::Float64Array>();
    Napi::Number second = info[1].As<Napi::Number>();
    Napi::Number third = info[2].As<Napi::Number>();
    Napi::Number fourth = info[3].As<Napi::Number>();
    Napi::Float64Array fifth = info[4].As<Napi::Float64Array>();
    Napi::Float64Array six = info[5].As<Napi::Float64Array>();
    Napi::Float64Array seven = info[6].As<Napi::Float64Array>();
    Napi::Number eight = info[7].As<Napi::Number>();
    Napi::Number nine = info[8].As<Napi::Number>();
    Napi::Number ten = info[9].As<Napi::Number>();
    Napi::Number eleven = info[10].As<Napi::Number>();
    Napi::Int32Array twelve = info[11].As<Napi::Int32Array>();
    Napi::Float64Array return_value = Napi::Float64Array::New(env, first.ByteLength() / 8);

    std::vector<double> val{Wrapper::simulate_multi_couple(
        first.Data(), second.Int32Value(), third.FloatValue(), fourth.FloatValue(),
        fifth.Data(), six.Data(), seven.Data(), eight.FloatValue(),
        nine.Int32Value(), ten.Int32Value(), eleven.Int32Value(), twelve.Data())};

    for (size_t i{0}; i < val.size(); i++)
        return_value.Set(i, val[i]);
    return return_value;
}

Napi::Array Wrapper::add_get_params(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env(); // check if arguments are integer only.
    std::array<std::string, 12> tmp{"tab_init:Float64Array", "R:Number",
                                   "Kernel_mu:Number",      "Kernel_sigma:Number",
                                   "bs:Float64Array",       "ms:Float64Array",
                                   "ss:Float64Array",       "time:Number",
                                   "width:Number",          "height:Number",
                                   "nb_couple:Number",      "nb_rings:Uint32Array"};

    Napi::Array return_value = Napi::Array::New(env, tmp.size());

    for (size_t i{0}; i < tmp.size(); i++)
        return_value[i] = Napi::String::New(env, tmp[i]);
    return return_value;
}

Napi::Object Wrapper::init(Napi::Env env, Napi::Object exports)
{

    exports.Set("simulate", Napi::Function::New(env, Wrapper::add_wrapped_multi_couple));
    exports.Set("get_params", Napi::Function::New(env, Wrapper::add_get_params));
    return exports;
}
