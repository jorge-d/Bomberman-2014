#ifndef __SCANDIR_HH_
# define __SCANDIR_HH_

#include <string>
#include <iostream>
#include <dirent.h>
#include <cstdio>
#include <vector>

class ScanDir
{
private:
  bool fail_;
  std::string path_;
  DIR *dp_;

public:
  ScanDir(const char *path = ".");
  ~ScanDir(void);
  bool getFilesFromExtension(std::vector<std::string>&, const std::string& = "") const;
  bool isOk(void) const;
  bool operator!(void) const;
};

#endif
