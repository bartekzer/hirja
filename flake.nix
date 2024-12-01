{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
  };

  outputs = {
    self,
    nixpkgs,
  }: let
    systems = ["x86_64-linux" "aarch64-linux" "x86_64-darwin"];
    forAllSystems = f:
      nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
  in {
    formatter = forAllSystems (pkgs: pkgs.alejandra);

    devShells = forAllSystems (pkgs: {
      default = pkgs.mkShell {
        packages = with pkgs; [gcc clang-tools];
      };
    });

    packages = forAllSystems (pkgs: {
      default = pkgs.stdenv.mkDerivation {
        name = "hirji";
        src = ./.;
        buildInputs = [pkgs.gcc pkgs.clang];

        buildPhase = ''
          gcc -o hirji ummalqura.c
        '';

        installPhase = ''
          mkdir -p $out/bin
          cp hirji $out/bin/
        '';
      };
    });
  };
}
