check_api_level_error=0
NNabla_api_level=`nnabla_cli function_info --api -1 | awk -F 'API_LEVEL: ' '{print $2}'`
Runtime_api_level=""

if [ ! $NNabla_api_level ]; then
  echo "nnabla_cli not found"
  exit -1
fi

for line in $($1/build/src/nnablart/nnablart version);
do
  if [[ $line =~ "API_LEVEL" ]]
  then
    Runtime_api_level=`echo $line | awk -F "_" '{print $3}' | sed "s/]//g"`
  fi
done

if [ "$NNabla_api_level" -ne "$Runtime_api_level" ];then
  echo "The api_level version of NNabla and NNabla-c-runtime are not synchronized." >&2
  check_api_level_error=1
fi
exit $check_api_level_error
