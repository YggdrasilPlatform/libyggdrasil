 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  *  _____.___.                 .___                    .__.__      *
  *  \__  |   | ____   ____   __| _/___________    _____|__|  |     *
  *   /   |   |/ ___\ / ___\ / __ |\_  __ \__  \  /  ___/  |  |     *
  *   \____   / /_/  > /_/  > /_/ | |  | \// __ \_\___ \|  |  |__   *
  *   / ______\___  /\___  /\____ | |__|  (____  /____  >__|____/   *
  *   \/     /_____//_____/      \/            \/     \/            *
  *                          - Common -                             *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
  * This software can be used by students and other personal of the *
  * Bern University of Applied Sciences under the terms of the MIT  *
  * license.                                                        *
  * For other persons this software is under the terms of the GNU   *
  * General Public License version 2.                               *
  *                                                                 *
  * Copyright &copy; 2021, Bern University of Applied Sciences.     *
  * All rights reserved.                                            *
  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
  *  @file common/result.hpp
  *  @ingroup common
  *  @author Fabian Weber, Nikolaij Saegesser
  *  @brief Result wrapper class
  */
#pragma once

#include <common/types.hpp>
#include <common/attributes.hpp>

#include <variant>
#include <optional>

struct ResultCode {
    constexpr ResultCode() : m_module(0), m_description(0) { }
    constexpr ResultCode(u16 module, u16 description) : m_module(module), m_description(description) { }

    [[nodiscard]] constexpr auto getModule() const noexcept { return this->m_module; }
    [[nodiscard]] constexpr auto getDescription()  const noexcept { return this->m_description; }

    [[nodiscard]] constexpr bool isSuccess() const noexcept { return this->m_module == 0 && this->m_description == 0; }
    [[nodiscard]] constexpr bool isFailure() const noexcept { return !isSuccess(); }

    [[nodiscard]] constexpr operator bool() { return isSuccess(); }

private:
    u16 m_module, m_description;
};

template<typename T>
struct Result {

    constexpr Result(const ResultCode &result) : m_data(result) { }
    constexpr Result(const T &value) : m_data(value) { }

    constexpr bool hasValue() const noexcept {
        return this->m_data.index() == 0;
    }

    constexpr operator bool() const noexcept {
        return hasValue();
    }

    constexpr ResultCode result() const noexcept {
        if (hasValue())
            return ResultCode(0, 0);
        else
            return std::get<1>(this->m_data);
    }

    constexpr T* get() {
        return std::get_if<0>(&this->m_data);
    }

    constexpr T* operator->() {
        return get();
    }

private:
    std::variant<T, ResultCode> m_data;
};
