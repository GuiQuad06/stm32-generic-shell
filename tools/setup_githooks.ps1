$hooksDirectory = Join-Path $PSScriptRoot '..\.git\hooks'

Get-ChildItem -LiteralPath (Join-Path $PSScriptRoot 'git_hooks') -File | ForEach-Object {
	New-Item -ItemType SymbolicLink -Path (Join-Path $hooksDirectory $_.BaseName) -Target $_.FullName
}
