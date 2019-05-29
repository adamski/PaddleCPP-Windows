set SolutionDir=%1
set TARG_CONFIG=%2
set TargetDir=%3

set FILE_LIST=(PaddleSDK StructureMap RGiesecke.DllExport.Metadata Newtonsoft.Json Interop.SHDocVw CredentialManagement)
set SRC_PATH=%SolutionDir%..\PaddleWrapper\PaddleWrapper\%TARG_CONFIG%
for %%i in %FILE_LIST% do (
	CALL :copy_file %SRC_PATH%,%%i.dll,%TargetDir%
)

CALL :copy_file %SRC_PATH%,PaddleWrapper.pdb,%TargetDir%

set PADDLECLR_PATH=%SolutionDir%..\PaddleCLR\PaddleCLR\%TARG_CONFIG%
CALL :copy_file %PADDLECLR_PATH%,PaddleCLR.pdb,%TargetDir%

EXIT /B %ERRORLEVEL%

:copy_file
set LOCAL_FILE=%~2
echo	Copying %LOCAL_FILE%...
copy "%~1\%LOCAL_FILE%" "%~3"
EXIT /B 0
