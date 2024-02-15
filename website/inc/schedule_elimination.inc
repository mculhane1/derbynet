<?php

// Normally we use max-runs-per-car = 0, so that each car runs once per lane.
// For some unusual situations, we want to limit to just 1 run per car (no
// matter which lane).  In that case, we first pad out the roster with BYEs so
// each car can get one run before we would start running anyone's second run.
// Then we form the rough schedule as a simple rotation chart (because the
// normal chart generators may put a given car only in heats that include a
// second run for some other car).  Finally, in make_ordered_schedule, we
// abandon those heats from the rough schedule that would cause any car to have
// second run.

require_once('inc/schedule_rough.inc');
require_once('inc/schedule_random.inc');
require_once('inc/schedule_utils.inc');
require_once('inc/schedule_one_round.inc');
require_once('inc/events.inc');


// The top-level elimination scheduling function.  Constructs a schedule, converts to a race
// chart, and writes the race chart into the database.
function schedule_elimination($roundid, $nlanes, $n_times_per_lane, $trace) {
  $roster = read_roster($roundid);
  $max_runs_per_car = 1;
  $sched = make_random_schedule($nlanes, count($roster), $n_times_per_lane,
                                 $max_runs_per_car, $trace);
  write_chart($roundid, spread_across_unused_lanes(form_chart($sched, $roster)));
  return true;
}

?>