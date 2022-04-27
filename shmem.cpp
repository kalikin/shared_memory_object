#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <string>
#include <iostream>

using namespace boost::interprocess;

int shmem(const std::string& name, bool remove) {
  if (remove) {
    std::cout << "removing shared_memory_object named \"" << name << "\"" << std::endl;
    if (shared_memory_object::remove(name.c_str())) {
      std::cout << "shared_memory_object was removed" << std::endl;
      return 0;
    }
    else {
      std::cout << "shared_memory_object was not removed" << std::endl;
      return 1;
    }
  }

  permissions unrestrictedPermissions;
  unrestrictedPermissions.set_unrestricted();

  std::cout << "creating shared_memory_object named \"" << name << "\"" << std::endl;
  std::cout << "permissions: " << std::oct << unrestrictedPermissions.get_permissions() << std::endl;

  shared_memory_object smo(open_or_create, name.c_str(), read_write, unrestrictedPermissions);

  std::cout << "success" << std::endl;

  return 0;
}


int main(int argc, char *argv[]) {
  std::string name;
  bool remove = false;

  for (int i = 1; i < argc; i++) {
    std::string arg = argv[i];
    if (arg == "--remove") {
      remove = true;
    }
    else if (name.empty()) {
      name = arg;
    }
    else {
      std::cout << "Unknown option: " << arg << std::endl;
      return 1;
    }
  }

  if (name.empty()) {
    std::cout << "Usage: " << argv[0] << " <name> [--remove]" << std::endl;
    return 1;
  }

  try {
    shmem(name, remove);
    return 0;
  }
  catch (...) {
    std::cout << "error: " << boost::current_exception_diagnostic_information() << std::endl;
    return 1;
  }
}
