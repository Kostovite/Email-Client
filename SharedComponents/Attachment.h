#pragma once

#include <string>
#include <fstream>

using std::string, std::ifstream;


class Attachment
{
private:
	string _fileName;
	string _filePath;
public:
	Attachment();
	Attachment(string fileName, string filePath);
	~Attachment();
	string getFileName();
	string getFilePath();
	string getFileType();
	void setFileName(string fileName);
	void setFilePath(string filePath);

	void printAttachmentDetails();
};