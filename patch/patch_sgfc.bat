dir patch\*.patch
for %%f in (patch\*.patch) do (
    git apply --directory sgfc %%f
)
