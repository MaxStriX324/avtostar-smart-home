param([string]$OutputDir = "")
$ErrorActionPreference = 'Stop'
$project = Join-Path $PSScriptRoot 'kicad'
$name = 'AVTOSTAR_ESP12F_Debug_Module'
$cli = Get-Command kicad-cli -ErrorAction SilentlyContinue
if ($cli) { $cli = $cli.Source } else { $cli = Join-Path $env:ProgramFiles 'KiCad\10.0\bin\kicad-cli.exe' }
if (-not (Test-Path -LiteralPath $cli -PathType Leaf)) { throw 'KiCad 10 CLI not found' }
if (-not $OutputDir) { $OutputDir = Join-Path $env:TEMP ("AVTOSTAR-audit-" + (Get-Date -Format 'yyyyMMdd-HHmmss')) }
New-Item -ItemType Directory -Path $OutputDir -Force | Out-Null
$sch = Join-Path $project ($name + '.kicad_sch')
$pcb = Join-Path $project ($name + '.kicad_pcb')
& $cli version
& $cli sch erc --exit-code-violations -o (Join-Path $OutputDir 'erc.rpt') $sch
$erc = $LASTEXITCODE
& $cli pcb drc --schematic-parity --exit-code-violations -o (Join-Path $OutputDir 'drc.rpt') $pcb
$drc = $LASTEXITCODE
& $cli pcb export step --output (Join-Path $OutputDir ($name + '.step')) $pcb
$step = $LASTEXITCODE
Write-Host "ERC=$erc DRC=$drc STEP=$step"
Write-Host "Reports: $OutputDir"
if ($erc -ne 0 -or $drc -ne 0 -or $step -ne 0) { exit 1 }
