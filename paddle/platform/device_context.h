/* Copyright (c) 2016 PaddlePaddle Authors. All Rights Reserve.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once
#include "paddle/framework/enforce.h"
#include "paddle/platform/place.h"
#include "unsupported/Eigen/CXX11/Tensor"

namespace paddle {
namespace platform {

class CPUDeviceContext;

class DeviceContext {
 public:
  virtual ~DeviceContext() {}

  template <typename DeviceType>
  DeviceType get_eigen_device();

  virtual Place GetPlace() const = 0;
};

template <>
Eigen::DefaultDevice DeviceContext::get_eigen_device<Eigen::DefaultDevice>() {
  return static_cast<CPUDeviceContext*>(this)->eigen_handle();
}

class CPUDeviceContext : public DeviceContext {
 public:
  Eigen::DefaultDevice eigen_handle() {
    if (!eigen_handle_) {
      eigen_handle_ = new Eigen::DefaultDevice();
    }
    return *eigen_handle_;
  }

  Place GetPlace() const override {
    Place retv = CPUPlace();
    return retv;
  }

 private:
  Eigen::DefaultDevice* eigen_handle_{nullptr};
};
}  // namespace platform
}  // namespace paddle
