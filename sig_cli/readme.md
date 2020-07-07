# Generate signature locally
 There are two directories for signature generation. The `botan` directory is the source code of the entire password library. We package the signature algorithm into a static library libbotan-2.a, and call the corresponding algorithm in `cli` to generate the signature and return pub/pri key.
