#include <particlepm.hpp>

using namespace PPM::Utils;

PPM_PACKAGE(p) {
  p->name("particlepm");
  p->version(PPM::Version("v0.1.7"));
  p->description("A package manager and build system for C/++ applications and libraries");
  p->github(PPM::GitHub("particletk", "particlepm"));
  p->license(PPM::License("MIT", "https://github.com/particletk/particlepm/blob/master/LICENSE.txt"));

  PPM::libs.insert("boost_program_options");
  PPM::libs.insert("boost_regex");

  // you can use
  //    p->git_repo(user, repo, selectors?)
  // or p->github_repo(name, url, selectors?)
  // or p->pkgconfig(name)
  // to specify dependencies

  PPM::TargetPtr lib = p->library("libparticlepm");
  lib->name("particlepm");
  lib->cpp("c++17");
  lib->cpp_files(std::vector<std::string> {
    "particlepm/dependency.cpp",
    "particlepm/github.cpp",
    "particlepm/libdeclarations.cpp",
    "particlepm/package.cpp",
    "particlepm/selector.cpp",
    "particlepm/utils.cpp",
    "particlepm/file.cpp",
    "particlepm/gitrepo.cpp",
    "particlepm/license.cpp",
    "particlepm/pkgconfig.cpp",
    "particlepm/target.cpp",
    "particlepm/version.cpp"
  });
  lib->cpp_flags(
    flagcat({
      "-ldl",

      "-lboost_regex",

      ("-I" + p->pkg_dir())
    })
  );

  PPM::TargetPtr exe = p->executable("particlepm");
  exe->cpp("c++17");
  exe->cpp_files(std::vector<std::string> {
    "main.cpp"
  });
  exe->cpp_flags(
    flagcat({
      ("-L" + PPM::dist_dir),

      "-lparticlepm",
      "-lboost_program_options",

      ("-I" + p->pkg_dir())
    })
  );
  exe->depends(lib);
}
