#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <Shlwapi.h>
#include <vector>


// for Directory::Exist
#pragma comment(lib, "Shlwapi.lib")

namespace SystemIO
{
	/// <summary>
	/// Exposes static methods for creating, moving, and enumerating through directories
	/// <para>and subdirectories.</para>
	/// </summary>
	static class Directory
	{
	public:

		/// <summary>
		/// Gets the current working directory of the application.
		/// </summary>
		/// <returns>A const wchar_t* that contains the absolute path of the current working directory, and
		/// <para>does not end with a backslash (\).</para>
		/// </returns>
		static const wchar_t* GetCurrentWorkingDirectory();

		/// <summary>
		/// Creates all directories and subdirectories in the specified path unless they
		/// <para>already exist.</para>
		/// </summary>
		/// <param name="path">The directory to create.</param>
		/// <returns>An object that represents the directory at the specified path. This object is
		/// <para>returned regardless of whether a directory at the specified path already exists.</para>
		/// </returns>
		static bool Create(const wchar_t* path);

		/// <summary>
		/// Determines whether the given path refers to an existing directory on disk.
		/// </summary>
		/// <param name="path">The path to test.</param>
		/// <returns>true if path refers to an existing directory; false if the directory does not
		/// <para>exist or an error occurs when trying to determine if the specified directory</para>
		/// <para>exists.</para>
		/// </returns>
		static bool Exists(const wchar_t* path);
	};

	/// <summary>
	/// Provides static methods for the creation, copying, deletion, moving, and opening
	/// <para>of a single file, and aids in the creation of System.IO objects.</para>
	/// </summary>
	static class File
	{
	public:

		/// <summary>
		/// Creates a new file at the specified path.
		/// <para>This function uses the Win32 API to create a new file at the specified path.</para>
		/// <para>The file is created with write access, and if a file already exists at the specified path,</para>
		/// <para>the function fails and returns false.</para>
		/// </summary>
		/// <param name="path">The path to the file to be created.</param>
		/// <returns>True if the file is created successfully, false otherwise.</returns>
		static bool Create(const wchar_t* path);

		/// <summary>
		/// Checks whether a file exists at the specified path.
		/// <para>This function utilizes the Win32 API to determine if a file exists at the given path.</para>
		/// </summary>
		/// <param name="path">The path to the file to be checked for existence.</param>
		/// <returns>True if the file exists, false otherwise.</returns>
		static bool Exists(const wchar_t* path);

		/// <summary>
		/// Reads the contents of a file into a vector of unsigned characters.
		/// <para>This function opens an existing file, reads its contents, and returns the data as a vector.</para>
		/// </summary>
		/// <param name="path">The path to the file to be read.</param>
		/// <returns>A vector containing the binary data read from the file. If the file reading operation fails, an empty vector is returned.</returns>
		static std::vector<unsigned char> ReadAllBytes(const wchar_t* path);

		/// <summary>
		/// Writes the given data to a file.
		/// <para>This function creates a new file or overwrites an existing file with the specified data.</para>
		/// </summary>
		/// <param name="path">The file to write to.</param>
		/// <param name="data">A vector containing the binary data to be written to the file.</param>
		/// <returns>True if the file writing operation is successful, false otherwise.</returns>
		static bool WriteAllBytes(const wchar_t* path, const std::vector<unsigned char>& data);
	};

	const wchar_t* Directory::GetCurrentWorkingDirectory()
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

	bool Directory::Create(const wchar_t* path)
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

	bool Directory::Exists(const wchar_t* path)
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

	std::vector<unsigned char> File::ReadAllBytes(const wchar_t* path)
	{
		HANDLE fileHandle = CreateFileW(
			path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			std::wcerr << L"Failed to open file: " << path << L"\r\n";
			return {};
		}

		DWORD fileSize = GetFileSize(fileHandle, NULL);

		std::vector<unsigned char> byteArray(fileSize);

		DWORD bytesRead;

		if (!ReadFile(fileHandle, byteArray.data(), fileSize, &bytesRead, NULL))
		{
			std::wcerr << L"File read error!: " << path << L"\r\n";
			byteArray.clear();
		}

		CloseHandle(fileHandle);

		return byteArray;
	}

	bool File::WriteAllBytes(const wchar_t* path, const std::vector<unsigned char>& data)
	{
		HANDLE fileHandle = CreateFileW(
			path,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			std::wcerr << L"Failed to create file: " << path << std::endl;
			return false;
		}

		DWORD bytesWritten;
		if (!WriteFile(fileHandle, data.data(), static_cast<DWORD>(data.size()), &bytesWritten, NULL))
		{
			std::wcerr << L"File writing failed." << std::endl;
			CloseHandle(fileHandle);
			return false;
		}

		CloseHandle(fileHandle);
		return true;
	}

	bool File::Create(const wchar_t* path)
	{
		HANDLE fileHandle = CreateFileW(
			path,
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_NEW, // Using CREATE_NEW to create a new file; fails if the file already exists
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		// Check if the file was created successfully
		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			std::wcerr << L"Failed to create file: " << path << std::endl;
			return false;
		}

		// Close the file handle
		CloseHandle(fileHandle);
		return true;
	}

	bool File::Exists(const wchar_t* path)
	{
		// Open the file
		HANDLE fileHandle = CreateFileW(
			path,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		// Check if the file exists
		if (fileHandle == INVALID_HANDLE_VALUE)
		{
			if (GetLastError() != ERROR_FILE_NOT_FOUND)
			{
				std::wcerr << L"Error checking file existence: " << path << std::endl;
			}
			CloseHandle(fileHandle);
			return false;;
		}

		// Close the file handle
		CloseHandle(fileHandle);
		return true;
	}
}
