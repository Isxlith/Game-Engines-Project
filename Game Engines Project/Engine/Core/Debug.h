#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Debug
{
public:
	enum class MessageType : unsigned short
	{
		// Starts at 0
		TYPE_NONE,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};

	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	static void OnCreate(const string& name_ = "GameEnginesDebugLog");
	static void SetSeverity(MessageType type_);
	static void Info(const string& message_, const string& fileName_, const int line_);
	static void Trace(const string& message_, const string& fileName_, const int line_);
	static void Warning(const string& message_, const string& fileName_, const int line_);
	static void Error(const string& message_, const string& fileName_, const int line_);
	static void FatalError(const string& message_, const string& fileName_, const int line_);

private:
	static void Log(const MessageType type_, const string& message_, const string& fileName_, const int line_);
	static MessageType currentSev;
	static string outputName;
};

#endif