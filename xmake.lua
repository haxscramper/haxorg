target("test_codegen", function() 
  set_kind("phony")
  on_build(function(target) 
    os.execv("conda", {"run", "-n", "main", "scripts/code/py_codegen/test_codegen.py"})
  end)
end)

target("download_llvm")
    set_kind("phony")

    on_build(function(target)
        -- Check if the directory exists
        if not os.isdir("toolchain/llvm") then
            print("LLVM not found. Downloading...")
            
            -- Download the archive
            os.exec("curl -L -o llvm.tar.xz https://github.com/llvm/llvm-project/releases/download/llvmorg-16.0.3/clang+llvm-16.0.3-x86_64-linux-gnu-ubuntu-22.04.tar.xz")
            
            -- Create the toolchain directory if it doesn't exist
            if not os.isdir("toolchain") then
                os.mkdir("toolchain")
            end

            -- Unpack the archive
            os.exec("tar -xf llvm.tar.xz -C toolchain && mv toolchain/clang+llvm-16.0.3-x86_64-linux-gnu-ubuntu-22.04 toolchain/llvm")

            -- Optionally, remove the downloaded archive
            os.rm("llvm.tar.xz")

            print("LLVM downloaded and unpacked successfully!")
        else
            print("LLVM already exists. Skipping download.")
        end
    end)
