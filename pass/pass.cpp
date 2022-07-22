#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/FileSystem.h"
#include <cstdlib>

using namespace llvm;

/**
 * @brief Dumps the module to the path preserving the original directory structure
 * 
 * @param M LLVM Module to dump
 * @param path Path to store the bit code
 * @note The dump file will still have the original file's extension but will contain the llvm bitcode.
 *       use llvm-dis to generate a human readable representation of the IR
 */
void dumpModuleToFile(llvm::Module& M, std::string& path){
  std::error_code EC;
  
  // Generate all the directories in path which are not generated
  auto filename_stripped_it = path.find_last_of('/');
  // Create directory if not exists
  std::string filename_stripped_path(path.begin(),path.begin()+filename_stripped_it);
  std::string dir_gen_command = "mkdir -p ";
  dir_gen_command += filename_stripped_path;
  std::system(dir_gen_command.c_str());


  // Write the file
  llvm::raw_fd_ostream  file(path,EC,llvm::sys::fs::OF_None);
  WriteBitcodeToFile(M,file);
}

namespace
{
  /**
   * @brief LLVM Pass
   * 
   */
  struct StandardPass : public ModulePass
  {
    static char ID;
    StandardPass() : ModulePass(ID) {}

    virtual bool runOnModule(Module &M)
    {
      llvm::errs() << "Module Name : " << M.getModuleIdentifier() << '\n';
    }
  };
}

char StandardPass::ID = 0;


// To be used when building kernel
// static RegisterStandardPasses Z(
//     PassManagerBuilder::EP_ModuleOptimizerEarly,
//     [](const PassManagerBuilder &Builder,
//        legacy::PassManagerBase &PM)
//     { PM.add(new MemoryPass()); });

// To be used when compiling a normal program
static RegisterStandardPasses Z(
    PassManagerBuilder::EP_EnabledOnOptLevel0,
    [](const PassManagerBuilder &Builder,
       legacy::PassManagerBase &PM) { PM.add(new StandardPass()); });
