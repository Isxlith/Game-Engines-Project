#include "Debug.h"

Debug::MessageType Debug::currentSev = MessageType::TYPE_NONE;
string Debug::outputName = "";

void Debug::OnCreate(const string& name_)
{
	outputName = name_ + ".txt";
	ofstream out;
	out.open(outputName.c_str(), ios::out);
	out.close();
	currentSev = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType type_)
{
	currentSev = type_;
}


// Calls Log function
void Debug::Info(const string& message_, const string& fileName_, const int line_)
{
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const string& message_, const string& fileName_, const int line_)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const string& message_, const string& fileName_, const int line_)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const string& message_, const string& fileName_, const int line_)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const string& message_, const string& fileName_, const int line_)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]: " + message_, fileName_, line_);
}

void Debug::Log(const MessageType type_, const string& message_, const string& fileName_, const int line_)
{
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE)
	{
		// Open and write to file, then close it
		ofstream out;
		out.open(outputName.c_str(), ios::app | ios::out);
		out << message_ << " in: " << fileName_ << " on line: " << line_ << endl;
		out.flush();
		out.close();
	}
}