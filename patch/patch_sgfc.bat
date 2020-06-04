@echo off
for %%f in (patch\*.patch) do (
    echo %%f
    git apply --directory sgfc %%f 2> nul && echo OK  && (cmd /c "exit /b 0") || (echo KO)
)
