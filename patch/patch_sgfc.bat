@echo off
for %%f in (..\patch\*.patch) do (
    git apply %%f & echo OK 
)
