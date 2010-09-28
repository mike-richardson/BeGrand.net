<?php
// $Id: cd-comment.tpl.php,v 1.1.2.2 2010/02/02 10:54:43 swentel Exp $

/**
 * @file
 * cd-comment.tpl.php Optimized version for cd and ds.
 */
?>

<div class="clear-block comment<?php if ($comment->status == COMMENT_NOT_PUBLISHED): print ' comment-unpublished'; endif; ?><?php if ($new != ''): ?> new <?php endif; ?>">
<div class="content"><?php print $content; ?></div></div>
