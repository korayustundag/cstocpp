#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <Shlwapi.h>


// for Directory::Exist
#pragma comment(lib, "Shlwapi.lib")

namespace SystemIO
{
	static class Directory
	{
	public:

		/// <summary>
		/// Gets the current working directory of the application.
		/// </summary>
		/// <returns>A const wchar_t* that contains the absolute path of the current working directory, and
		/// <para>does not end with a backslash (\).</para>
		/// </returns>
		static const wchar_t* GetCurrentWorkingDirectory()
		{
			constexpr DWORD bufferSize = MAX_PATH;
			wchar_t* buffer = new wchar_t[bufferSize];
			DWORD length = GetCurrentDirectory(bufferSize, buffer);

			if (length == 0)
			{
				std::cerr << "GetCurrentWorkingDirectory failed with error code " << GetLastError() << std::endl;
				delete[] buffer;
				return nullptr;
			}
			return buffer;
		}

		/// <summary>
		/// Creates all directories and subdirectories in the specified path unless they
		/// <para>already exist.</para>
		/// </summary>
		/// <param name="path">The directory to create.</param>
		/// <returns>An object that represents the directory at the specified path. This object is
		/// <para>returned regardless of whether a directory at the specified path already exists.</para>
		/// </returns>
		static bool Create(const wchar_t* path)
		{
			if (CreateDirectory(path, NULL) || GetLastError() == ERROR_ALREADY_EXISTS)
			{
				return true;
			}
			else
			{
				std::cerr << "Failed to create folder. Error code: " << GetLastError() << std::endl;
				return false;
			}
		}

		/// <summary>
		/// Determines whether the given path refers to an existing directory on disk.
		/// </summary>
		/// <param name="path">The path to test.</param>
		/// <returns>true if path refers to an existing directory; false if the directory does not
		/// <para>exist or an error occurs when trying to determine if the specified directory</para>
		/// <para>exists.</para>
		/// </returns>
		static bool Exists(const wchar_t* path)
		{
			if (PathFileExists(path))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};
}
