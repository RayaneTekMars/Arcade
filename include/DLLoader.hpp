/*
** EPITECH PROJECT, 2022
** Arcade
** File description:
** DLLoader
*/

#pragma once

#include "ModuleType.hpp"

#include <dlfcn.h>
#include <exception>
#include <iostream>

namespace Arcade
{
    /**
     * @class DLLoader
     * @brief DLLoader class encapsulate the c dynamic library functions
     */
    class DLLoader
    {
        public:

            class Exception : std::exception
            {
                public:

                    Exception(const std::string &message) : m_message(message) {}
                    ~Exception() {}

                    const char *what() const noexcept { return (m_message.c_str()); }

                private:

                    std::string m_message;
            };

        public:

            /**
             * @brief Constructor
             */
            DLLoader() : m_handle(nullptr) {}

            /**
             * @brief Destructor
             * unload the library if it is loaded
             */
            ~DLLoader()
            {
                try {
                    unload();
                } catch (Exception e) {
                    std::cerr << e.what() << std::endl;
                } catch (...) {
                    std::cerr << "~DLLoader(): unknown exception" << std::endl;
                }
            }

            /**
             * @brief load the library
             * @param path the path to the library
             */
            void load(const std::string &libPath)
            {
                unload();
                if (!(m_handle = dlopen(libPath.c_str(), RTLD_NOW)))
                    throw Exception(std::string("load(): ") + dlerror());
            }

            /**
             * @brief unload the library
             */
            void unload()
            {
                if (m_handle) {
                    if (dlclose(m_handle) != 0) {
                        m_handle = nullptr;
                        throw Exception(std::string("unload(): ") + dlerror());
                    }
                    m_handle = nullptr;
                }
            }

            /**
             * @brief get the library type
             * @param typeSym the symbol name to get the library type
             * @return the library type of the library
             */
            ModuleType getType(const std::string &typeSym = "getType")
            {
                if (!m_handle)
                    throw Exception("getType(): no library loaded");
                auto sym = dlsym(m_handle, typeSym.c_str());
                if (!sym)
                    throw Exception(std::string("getType(): ") + dlerror());
                return ((ModuleType(*)())sym)();
            }

            /**
             * @brief get a library instance
             * @param entryPointSym the symbol name to get a library instance
             * @return a instance
             */
            template<typename T>
            T *getInstance(const std::string &entryPointSym = "entryPoint")
            {
                if (!m_handle)
                    throw Exception("getInstance(): no library loaded");
                auto sym = dlsym(m_handle, entryPointSym.c_str());
                if (!sym)
                    throw Exception(std::string("getInstance(): ") + dlerror());
                return ((T * (*)()) sym)();
            }

        private:

            void *m_handle;
    };
} // namespace Arcade