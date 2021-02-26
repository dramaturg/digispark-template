with import <nixpkgs> {};

pkgs.mkShell {
  buildInputs = with pkgs; [
    git
    libusb1
    platformio
    micronucleus
  ];
}
