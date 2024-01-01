#pragma once
#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <Shlobj.h>

// for warning C4091: 'static'
#pragma warning(disable:4091)


namespace System
{
#define NewLine "\r\n"

	static class Console
	{
	public:
		/// <summary>
		/// Writes the specified string value to the standard output stream.
		/// </summary>
		/// <param name="value">The value to write.</param>
		static void Write(const char* value)
		{
			std::cout << value;
		}

		/// <summary>
		/// Writes the specified string value to the standard output stream.
		/// </summary>
		/// <param name="value">The value to write.</param>
		static void Write(const wchar_t* value)
		{
			HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
			WriteConsoleW(hc, value, static_cast<DWORD>(wcslen(value)), NULL, NULL);
		}

		/// <summary>
		/// Writes the current line terminator to the standard output stream.
		/// </summary>
		static void WriteLine()
		{
			std::cout << NewLine;
		}

		/// <summary>
		/// Writes the specified string value, followed by the current line terminator, to
		/// <para>the standard output stream.</para>
		/// </summary>
		/// <param name="value">The value to write.</param>
		static void WriteLine(const char* value)
		{
			std::cout << value << NewLine;
		}

		/// <summary>
		/// Writes the specified string value, followed by the current line terminator, to
		/// <para>the standard output stream.</para>
		/// </summary>
		/// <param name="value">The value to write.</param>
		static void WriteLine(const wchar_t* value)
		{
			HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
			WriteConsoleW(hc, value, static_cast<DWORD>(wcslen(value)), NULL, NULL);
			WriteLine();
		}
	};

	static class Environment
	{
	public:

		/// <summary>
		/// Specifies enumerated constants used to retrieve directory paths to system special folders.
		/// </summary>
		enum SpecialFolder
		{
			/// <summary>
			/// The file system directory that is used to store administrative tools for an individual user. The Microsoft Management Console (MMC) will save customized consoles to this directory, and it will roam with the user.
			/// </summary>
			AdminTools = 48,

			/// <summary>
			/// The directory that serves as a common repository for application-specific data for the current roaming user. A roaming user works on more than one computer on a network. A roaming user's profile is kept on a server on the network and is loaded onto a system when the user logs on.
			/// </summary>
			ApplicationData = 26,

			/// <summary>
			/// The file system directory that contains administrative tools for all users of the computer.
			/// </summary>
			CommonAdminTools = 47,

			/// <summary>
			/// The directory that serves as a common repository for application-specific data that is used by all users.
			/// </summary>
			CommonApplicationData = 35,

			/// <summary>
			/// The file system directory that contains files and folders that appear on the desktop for all users.
			/// </summary>
			CommonDesktopDirectory = 25,

			/// <summary>
			/// The file system directory that contains documents that are common to all users.
			/// </summary>
			CommonDocuments = 46,

			/// <summary>
			/// The file system directory that serves as a repository for music files common to all users.
			/// </summary>
			CommonMusic = 53,

			/// <summary>
			/// The file system directory that serves as a repository for image files common to all users.
			/// </summary>
			CommonPictures = 54,

			/// <summary>
			/// The directory for components that are shared across applications.
			/// <para>To get the x86 common program files directory in a non-x86 process, use the ProgramFilesX86 member.</para>
			/// </summary>
			CommonProgramFiles = 43,

			/// <summary>
			/// The Program Files folder.
			/// </summary>
			CommonProgramFilesX86 = 44,

			/// <summary>
			/// The logical Desktop rather than the physical file system location.
			/// </summary>
			Desktop = 0,

			/// <summary>
			/// The directory used to physically store file objects on the desktop. Do not confuse this directory with the desktop folder itself, which is a virtual folder.
			/// </summary>
			DesktopDirectory = 16,

			/// <summary>
			/// The directory that serves as a common repository for application-specific data that is used by the current, non-roaming user.
			/// </summary>
			LocalApplicationData = 28,

			/// <summary>
			/// The My Documents folder.
			/// </summary>
			MyDocuments = 5,

			/// <summary>
			/// The My Music folder.
			/// </summary>
			MyMusic = 13,

			/// <summary>
			/// The My Pictures folder.
			/// </summary>
			MyPictures = 39,

			/// <summary>
			/// The file system directory that serves as a repository for videos that belong to a user.
			/// </summary>
			MyVideos = 14,

			/// <summary>
			/// The program files directory.
			/// <para>To get the x86 program files directory in a non-x86 process, use the ProgramFilesX86 member.</para>
			/// </summary>
			ProgramFiles = 38,

			/// <summary>
			/// The x86 Program Files folder.
			/// </summary>
			ProgramFilesX86 = 42,

			/// <summary>
			/// The System directory.
			/// </summary>
			System = 37,

			/// <summary>
			/// The Windows System folder.
			/// </summary>
			SystemX86 = 41,

			/// <summary>
			/// The Windows directory or SYSROOT. This corresponds to the %windir% or %SYSTEMROOT% environment variables.
			/// </summary>
			Windows = 36
		};

		/// <summary>
		/// Terminates this process and returns an exit code to the operating system.
		/// </summary>
		/// <param name="code">The exit code to return to the operating system. Use 0 (zero) to indicate that<para>the process completed successfully.</para></param>
		static void Exit(int code)
		{
			Console::Write("Press [enter] to exit...");
			std::cin.get();
			exit(code);
		}

		/// <summary>
		/// Determines whether the current operating system is a 64-bit operating system.
		/// </summary>
		/// <returns>true if the operating system is 64-bit; otherwise, false.</returns>
		static bool Is64BitOperatingSystem()
		{
			BOOL is64Bit = FALSE;
			if (IsWow64Process(GetCurrentProcess(), &is64Bit) && is64Bit)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary>
		/// Determines whether the current process is a 64-bit process.
		/// </summary>
		/// <returns>true if the process is 64-bit; otherwise, false.</returns>
		static bool Is64BitProcess()
		{
			SYSTEM_INFO systemInfo;
			GetNativeSystemInfo(&systemInfo);
			if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
			{
				return true;
			}
			else
			{
				return false;
			}
		}


		/// <summary>
		/// Gets the path to the system special folder that is identified by the specified enumeration.
		/// </summary>
		/// <param name="folder">One of the enumeration values that identifies a system special folder.</param>
		/// <returns>
		/// <see langword="const wchar_t"/>
		/// <para>The path to the specified system special folder, if that folder physically exists on your computer; otherwise, an empty const wchar_t* ("").</para>
		/// <para>A folder will not physically exist if the operating system did not create it, the existing folder was deleted, or the folder is a virtual directory, such as My Computer, which does not correspond to a physical path.</para>
		/// </returns>
		static const wchar_t* GetFolderPath(SpecialFolder folder)
		{
			switch (folder)
			{
			case Environment::AdminTools:
				return GetFolder(Environment::AdminTools);
				break;
			case Environment::ApplicationData:
				return GetFolder(Environment::ApplicationData);
				break;
			case Environment::CommonAdminTools:
				return GetFolder(Environment::CommonAdminTools);
				break;
			case Environment::CommonApplicationData:
				return GetFolder(Environment::CommonApplicationData);
				break;
			case Environment::CommonDesktopDirectory:
				return GetFolder(Environment::CommonDesktopDirectory);
				break;
			case Environment::CommonDocuments:
				return GetFolder(Environment::CommonDocuments);
				break;
			case Environment::CommonMusic:
				return GetFolder(Environment::CommonMusic);
				break;
			case Environment::CommonPictures:
				return GetFolder(Environment::CommonPictures);
				break;
			case Environment::CommonProgramFiles:
				return GetFolder(Environment::CommonProgramFiles);
				break;
			case Environment::CommonProgramFilesX86:
				return GetFolder(Environment::CommonProgramFilesX86);
				break;
			case Environment::Desktop:
				return GetFolder(Environment::Desktop);
				break;
			case Environment::DesktopDirectory:
				return GetFolder(Environment::DesktopDirectory);
				break;
			case Environment::LocalApplicationData:
				return GetFolder(Environment::LocalApplicationData);
				break;
			case Environment::MyDocuments:
				return GetFolder(Environment::MyDocuments);
				break;
			case Environment::MyMusic:
				return GetFolder(Environment::MyMusic);
				break;
			case Environment::MyPictures:
				return GetFolder(Environment::MyPictures);
				break;
			case Environment::MyVideos:
				return GetFolder(Environment::MyVideos);
				break;
			case Environment::ProgramFiles:
				return GetFolder(Environment::ProgramFiles);
				break;
			case Environment::ProgramFilesX86:
				return GetFolder(Environment::ProgramFilesX86);
				break;
			case Environment::System:
				return GetFolder(Environment::System);
				break;
			case Environment::SystemX86:
				return GetFolder(Environment::SystemX86);
				break;
			case Environment::Windows:
				return GetFolderWin();
				break;
			default:
				return L"";
				break;
			}
		}

	private:
		static const wchar_t* GetFolder(int cc)
		{
			const int bufferSize = MAX_PATH;
			wchar_t* dir = new wchar_t[bufferSize];
			if (SHGetSpecialFolderPathW(0, dir, cc, FALSE) == 0)
			{
				delete[] dir;
				return nullptr;
			}
			return dir;
		}

		static const wchar_t* GetFolderWin()
		{
			const int bufferSize = MAX_PATH;
			wchar_t* dir = new wchar_t[bufferSize];
			if (GetWindowsDirectoryW(dir, bufferSize) == 0)
			{
				delete[] dir;
				return nullptr;
			}
			return dir;
		}
	};
}
