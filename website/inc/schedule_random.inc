<?php

require_once('inc/schedule_rough.inc');

// RACE_COUNT_WEIGHT is the weight (penalty) for uneven race counts.  That is,
// when some racers have raced a lot more than others, RACE_COUNT_WEIGHT scales
// the deviation from a preferred condition of having the same race count for
// all racers.
define('RACE_COUNT_WEIGHT', 10);
// CONSECUTIVE_WEIGHT is the weight applied when a car appears in consecutive
// heats.
define('CONSECUTIVE_WEIGHT', 1000);
// CONSECUTIVE_WEIGHT + REPEAT_WEIGHT is the weight if a car appears in the same
// lane in consecutive heats.
define('REPEAT_WEIGHT', 1000);


// Starts with the rough schedule (as produced by generator(s)), and then
// reorders the heats to optimize goals of keeping even race counts, and
// avoiding consecutive races for the same racer.
function make_random_schedule($nlanes, $ncars, $n_times_per_lane,
                               $max_runs_per_car, $trace) {

  $heat_count = ceil($ncars / $nlanes);
  $heat_size = ceil($ncars / $heat_count);
  $full_heats = $heat_count - (($heat_count * $heat_size) - $ncars);

  $cars = range(0, $ncars-1);
  $heats = array();

  shuffle($cars);
  for ($i =0; $i < $heat_count; ++$i) {
      if ($i < $full_heats) {
		$heats[] = array_splice($cars, 0, $heat_size);
      } else {
        $heat = array_splice($cars, 0, $heat_size-1);
        array_push($heat, null);
		$heats[] = $heat;
      }


  }
  if(count($cars) > 0) {
      json_failure('failure', 'Cars remaining');
      return array();
  }

  return $heats;
}

?>