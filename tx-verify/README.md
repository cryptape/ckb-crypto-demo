## introduce
generate a mocked tx

## request
- ruby
- bundler
- ckb-cli
## usage 

###  install deps
`bundler install`

### Generate and verify
- generate
`bundler exec ./tx-mock.rb {path-of-code}`

- verify via ckb-cli
`ckb-cli mock-tx  verify --tx-file=tx-mocked.json`

