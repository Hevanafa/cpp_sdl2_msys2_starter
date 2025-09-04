use strict;
use warnings;
use 5.32.1;

use Cwd;
say Cwd::cwd;

sub build_project {
  my $gpp_path = "C:\\msys64\\ucrt64\\bin\\c++.exe";
  my $output_dir = "dist";
  my $output_file = "main.exe";

  my @args = (
    $gpp_path,
    "-Iinclude",
    "-g",
    "src\\main.cpp",
    "src\\Game.cpp",
    "-o",
    $output_dir."\\".$output_file,
    "-lmingw32",
    "-lSDL2main",
    "-lSDL2"
  );

  mkdir $output_dir if !(-d $output_dir);

  my $cmd_line = join " ", @args;
  say $cmd_line;
  
  # TODO: This doesn't output anything
  # system @args;
  my $output = `$cmd_line`;
  say $output
}

my $command = $ARGV[0];

if ($command eq "build") {
  build_project
} elsif ($command eq "notepad") {
  system "notepad.exe"
}
