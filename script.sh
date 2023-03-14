./philo 4 501 250 250 3 > test
echo "Philo 1"
cat test | grep "1 is eating" | wc -l
echo "Philo 2"
cat test | grep "2 is eating" | wc -l
echo "Philo 3"
cat test | grep "3 is eating" | wc -l
echo "Philo 4"
cat test | grep "4 is eating" | wc -l
#--tool=helgrind