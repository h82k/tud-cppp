# Source: http://pshscripts.blogspot.co.uk/2012/11/convert-pptxtopdfps1.html
<# 
.SYNOPSIS 
    This function converts a PPTx file into a PDF file 
.DESCRIPTION 
    The Convert-PptxToPDF function first creates an  
    instance of PowerPoint, opens the $ifile and saves 
    this to $ofile as a PDF file. 
.NOTES 
    File Name  : Convert-PptxToPDF 
    Author     : Thomas Lee - tfl@psp.co.uk 
    Requires   : PowerShell Version 3.0, Office 2010 
.LINK 
    This script posted to: 
        http://www.pshscripts.blogspot.com 
     
.EXAMPLE 
    There is nothing to see, except a set of new PDF Files in the output folder         
 
#> 
 
Function Convert-PptxToPDF { 
 
    [CmdletBinding()] 
    Param( 
    $IFile, 
    $OFile 
    ) 
     
    # add key assemblies 
    Add-type -AssemblyName office -ErrorAction SilentlyContinue 
    Add-Type -AssemblyName microsoft.office.interop.powerpoint -ErrorAction SilentlyContinue 
     
    # Open PowerPoint 
    $ppt = new-object -comobject powerpoint.application 
    $ppt.visible = [Microsoft.Office.Core.MsoTriState]::msoTrue 
     
     
    # Open the presentation 
    $pres = $ppt.Presentations.Open($ifile,
         [Microsoft.Office.Core.MsoTriState]::msoTrue, # read-only
         [Microsoft.Office.Core.MsoTriState]::msoFalse, # Untitled
         [Microsoft.Office.Core.MsoTriState]::msoFalse # headless
        ) 
     
    # Now save it away as PDF 
    $opt= [Microsoft.Office.Interop.PowerPoint.PpSaveAsFileType]::ppSaveAsPDF 
    $pres.SaveAs($ofile,$opt,
        [Microsoft.Office.Core.MsoTriState]::msoTrue # embed True-Type fonts
        ) 
     
    # and Tidy-up 
    $pres.Close() 
    $ppt.Quit() 
    $ppt=$null 
 
} 


$root = ($pwd).Path
$folder = "Vorlesung" 

Foreach ($ifile in $(ls "$root\$folder" -Filter "*.pptx")) { 
  # Build name of output file 
  $pathname = split-path $ifile 
  $filename = split-path $ifile -leaf  
  $file     = $filename.split(".")[0] 
  $ofile    = $pathname + $file + ".pdf" 
 
  $fullInputPath = "$root\$folder\$iFile"
  $fullOutputPath = "$root\$folder\$oFile"
  echo "Checking..."
  
  $lastWriteForInput = (Get-Item $fullInputPath).LastWriteTime
  $lastWriteForOutput = (Get-Item $fullOutputPath).LastWriteTime
  if ($lastWriteForInput -gt $lastWriteForOutput) {
    echo "  [$oFile] Converting..."
    Convert-PptxToPDF -ifile $fullInputPath -OFile $fullOutputPath
  } else {
    echo "  [$oFile] Already up-to-date"
  }
} 
